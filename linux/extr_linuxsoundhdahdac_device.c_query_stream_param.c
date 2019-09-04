#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hdac_device {int /*<<< orphan*/  afg; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_PAR_STREAM ; 
 unsigned int snd_hdac_read_parm (struct hdac_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int query_stream_param(struct hdac_device *codec, hda_nid_t nid)
{
	unsigned int streams = snd_hdac_read_parm(codec, nid, AC_PAR_STREAM);

	if (!streams || streams == -1)
		streams = snd_hdac_read_parm(codec, codec->afg, AC_PAR_STREAM);
	if (!streams || streams == -1)
		return 0;
	return streams;
}