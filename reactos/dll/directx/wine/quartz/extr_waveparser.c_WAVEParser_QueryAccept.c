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
struct TYPE_3__ {int /*<<< orphan*/  subtype; int /*<<< orphan*/  majortype; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ AM_MEDIA_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ IsEqualIID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MEDIASUBTYPE_AIFF ; 
 int /*<<< orphan*/  MEDIASUBTYPE_AU ; 
 int /*<<< orphan*/  MEDIASUBTYPE_WAVE ; 
 int /*<<< orphan*/  MEDIATYPE_Stream ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT WAVEParser_QueryAccept(LPVOID iface, const AM_MEDIA_TYPE * pmt)
{
    if (!IsEqualIID(&pmt->majortype, &MEDIATYPE_Stream))
	return S_FALSE;
    if (IsEqualIID(&pmt->subtype, &MEDIASUBTYPE_WAVE))
        return S_OK;
    if (IsEqualIID(&pmt->subtype, &MEDIASUBTYPE_AU) || IsEqualIID(&pmt->subtype, &MEDIASUBTYPE_AIFF))
	FIXME("AU and AIFF files not supported yet!\n");
    return S_FALSE;
}