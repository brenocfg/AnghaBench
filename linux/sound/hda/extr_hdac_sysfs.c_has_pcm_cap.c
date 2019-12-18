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
struct hdac_device {scalar_t__ afg; scalar_t__ mfg; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
#define  AC_WID_AUD_IN 129 
#define  AC_WID_AUD_OUT 128 
 int /*<<< orphan*/  get_wcaps (struct hdac_device*,scalar_t__) ; 
 int get_wcaps_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool has_pcm_cap(struct hdac_device *codec, hda_nid_t nid)
{
	if (nid == codec->afg || nid == codec->mfg)
		return true;
	switch (get_wcaps_type(get_wcaps(codec, nid))) {
	case AC_WID_AUD_OUT:
	case AC_WID_AUD_IN:
		return true;
	default:
		return false;
	}
}