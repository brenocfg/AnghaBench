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
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 unsigned int AC_PINCAP_VREF ; 
 unsigned int AC_PINCAP_VREF_100 ; 
 unsigned int AC_PINCAP_VREF_GRD ; 
 unsigned int AC_PINCAP_VREF_SHIFT ; 
 unsigned int snd_hda_query_pin_caps (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int get_vref_caps(struct hda_codec *codec, hda_nid_t pin)
{
	unsigned int pincap;

	pincap = snd_hda_query_pin_caps(codec, pin);
	pincap = (pincap & AC_PINCAP_VREF) >> AC_PINCAP_VREF_SHIFT;
	/* filter out unusual vrefs */
	pincap &= ~(AC_PINCAP_VREF_GRD | AC_PINCAP_VREF_100);
	return pincap;
}