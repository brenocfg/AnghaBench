#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dwMciTimeFormat; } ;
typedef  TYPE_1__ WINE_MCIMIDI ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
#define  MCI_FORMAT_MILLISECONDS 131 
#define  MCI_FORMAT_SMPTE_24 130 
#define  MCI_FORMAT_SMPTE_25 129 
#define  MCI_FORMAT_SMPTE_30 128 
 int TIME_MS_IN_ONE_HOUR ; 
 int TIME_MS_IN_ONE_MINUTE ; 
 int TIME_MS_IN_ONE_SECOND ; 
 int /*<<< orphan*/  WARN (char*,int) ; 

__attribute__((used)) static	DWORD	MIDI_ConvertMSToTimeFormat(WINE_MCIMIDI* wmm, DWORD _val)
{
    DWORD	ret = 0, val = _val;
    DWORD	h, m, s, f;

    switch (wmm->dwMciTimeFormat) {
    case MCI_FORMAT_MILLISECONDS:
	ret = val;
	break;
    case MCI_FORMAT_SMPTE_24:
    case MCI_FORMAT_SMPTE_25:
    case MCI_FORMAT_SMPTE_30:
	h = val / TIME_MS_IN_ONE_HOUR;
	m = (val -= h * TIME_MS_IN_ONE_HOUR)   / TIME_MS_IN_ONE_MINUTE;
	s = (val -= m * TIME_MS_IN_ONE_MINUTE) / TIME_MS_IN_ONE_SECOND;
	switch (wmm->dwMciTimeFormat) {
	case MCI_FORMAT_SMPTE_24:
	    /* one frame is 1000/24 val long, 1000/24 == 125/3 */
	    f = (val * 3) / 125; 	val -= (f * 125) / 3;
	    break;
	case MCI_FORMAT_SMPTE_25:
	    /* one frame is 1000/25 ms long, 1000/25 == 40 */
	    f = val / 40; 		val -= f * 40;
	    break;
	case MCI_FORMAT_SMPTE_30:
	    /* one frame is 1000/30 ms long, 1000/30 == 100/3 */
	    f = (val * 3) / 100; 	val -= (f * 100) / 3;
	    break;
	default:
	    FIXME("There must be some bad bad programmer\n");
	    f = 0;
	}
	/* val contains the number of ms which cannot make a complete frame */
	/* FIXME: is this correct ? programs seem to be happy with that */
	ret = (f << 24) | (s << 16) | (m << 8) | (h << 0);
	break;
    default:
	WARN("Bad time format %u!\n", wmm->dwMciTimeFormat);
    }
    /*
      TRACE("val=%u [tf=%u] => ret=%u=0x%08x\n", _val, wmm->dwMciTimeFormat, ret, ret);
    */
    return ret;
}