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

/* Variables and functions */
 int /*<<< orphan*/  ADD (char*,char*,int,int) ; 
 int /*<<< orphan*/  DEF_FIELD (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DEF_FIELD_ADDR (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INPUT_DEVICE_ID_ABS_MAX ; 
 int /*<<< orphan*/  INPUT_DEVICE_ID_EV_MAX ; 
 int /*<<< orphan*/  INPUT_DEVICE_ID_FF_MAX ; 
 int /*<<< orphan*/  INPUT_DEVICE_ID_KEY_MAX ; 
 int /*<<< orphan*/  INPUT_DEVICE_ID_KEY_MIN_INTERESTING ; 
 int /*<<< orphan*/  INPUT_DEVICE_ID_LED_MAX ; 
 int INPUT_DEVICE_ID_MATCH_ABSBIT ; 
 int INPUT_DEVICE_ID_MATCH_BUS ; 
 int INPUT_DEVICE_ID_MATCH_EVBIT ; 
 int INPUT_DEVICE_ID_MATCH_FFBIT ; 
 int INPUT_DEVICE_ID_MATCH_KEYBIT ; 
 int INPUT_DEVICE_ID_MATCH_LEDBIT ; 
 int INPUT_DEVICE_ID_MATCH_MSCIT ; 
 int INPUT_DEVICE_ID_MATCH_PRODUCT ; 
 int INPUT_DEVICE_ID_MATCH_RELBIT ; 
 int INPUT_DEVICE_ID_MATCH_SNDBIT ; 
 int INPUT_DEVICE_ID_MATCH_SWBIT ; 
 int INPUT_DEVICE_ID_MATCH_VENDOR ; 
 int INPUT_DEVICE_ID_MATCH_VERSION ; 
 int /*<<< orphan*/  INPUT_DEVICE_ID_MSC_MAX ; 
 int /*<<< orphan*/  INPUT_DEVICE_ID_REL_MAX ; 
 int /*<<< orphan*/  INPUT_DEVICE_ID_SND_MAX ; 
 int /*<<< orphan*/  INPUT_DEVICE_ID_SW_MAX ; 
 int /*<<< orphan*/ * absbit ; 
 int bustype ; 
 int /*<<< orphan*/  do_input (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * evbit ; 
 int /*<<< orphan*/ * ffbit ; 
 int flags ; 
 int /*<<< orphan*/  input_device_id ; 
 int /*<<< orphan*/ * keybit ; 
 int /*<<< orphan*/ * ledbit ; 
 int /*<<< orphan*/ * mscbit ; 
 int product ; 
 int /*<<< orphan*/ * relbit ; 
 int /*<<< orphan*/ * sndbit ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/ * swbit ; 
 int vendor ; 
 int version ; 

__attribute__((used)) static int do_input_entry(const char *filename, void *symval,
			  char *alias)
{
	DEF_FIELD(symval, input_device_id, flags);
	DEF_FIELD(symval, input_device_id, bustype);
	DEF_FIELD(symval, input_device_id, vendor);
	DEF_FIELD(symval, input_device_id, product);
	DEF_FIELD(symval, input_device_id, version);
	DEF_FIELD_ADDR(symval, input_device_id, evbit);
	DEF_FIELD_ADDR(symval, input_device_id, keybit);
	DEF_FIELD_ADDR(symval, input_device_id, relbit);
	DEF_FIELD_ADDR(symval, input_device_id, absbit);
	DEF_FIELD_ADDR(symval, input_device_id, mscbit);
	DEF_FIELD_ADDR(symval, input_device_id, ledbit);
	DEF_FIELD_ADDR(symval, input_device_id, sndbit);
	DEF_FIELD_ADDR(symval, input_device_id, ffbit);
	DEF_FIELD_ADDR(symval, input_device_id, swbit);

	sprintf(alias, "input:");

	ADD(alias, "b", flags & INPUT_DEVICE_ID_MATCH_BUS, bustype);
	ADD(alias, "v", flags & INPUT_DEVICE_ID_MATCH_VENDOR, vendor);
	ADD(alias, "p", flags & INPUT_DEVICE_ID_MATCH_PRODUCT, product);
	ADD(alias, "e", flags & INPUT_DEVICE_ID_MATCH_VERSION, version);

	sprintf(alias + strlen(alias), "-e*");
	if (flags & INPUT_DEVICE_ID_MATCH_EVBIT)
		do_input(alias, *evbit, 0, INPUT_DEVICE_ID_EV_MAX);
	sprintf(alias + strlen(alias), "k*");
	if (flags & INPUT_DEVICE_ID_MATCH_KEYBIT)
		do_input(alias, *keybit,
			 INPUT_DEVICE_ID_KEY_MIN_INTERESTING,
			 INPUT_DEVICE_ID_KEY_MAX);
	sprintf(alias + strlen(alias), "r*");
	if (flags & INPUT_DEVICE_ID_MATCH_RELBIT)
		do_input(alias, *relbit, 0, INPUT_DEVICE_ID_REL_MAX);
	sprintf(alias + strlen(alias), "a*");
	if (flags & INPUT_DEVICE_ID_MATCH_ABSBIT)
		do_input(alias, *absbit, 0, INPUT_DEVICE_ID_ABS_MAX);
	sprintf(alias + strlen(alias), "m*");
	if (flags & INPUT_DEVICE_ID_MATCH_MSCIT)
		do_input(alias, *mscbit, 0, INPUT_DEVICE_ID_MSC_MAX);
	sprintf(alias + strlen(alias), "l*");
	if (flags & INPUT_DEVICE_ID_MATCH_LEDBIT)
		do_input(alias, *ledbit, 0, INPUT_DEVICE_ID_LED_MAX);
	sprintf(alias + strlen(alias), "s*");
	if (flags & INPUT_DEVICE_ID_MATCH_SNDBIT)
		do_input(alias, *sndbit, 0, INPUT_DEVICE_ID_SND_MAX);
	sprintf(alias + strlen(alias), "f*");
	if (flags & INPUT_DEVICE_ID_MATCH_FFBIT)
		do_input(alias, *ffbit, 0, INPUT_DEVICE_ID_FF_MAX);
	sprintf(alias + strlen(alias), "w*");
	if (flags & INPUT_DEVICE_ID_MATCH_SWBIT)
		do_input(alias, *swbit, 0, INPUT_DEVICE_ID_SW_MAX);
	return 1;
}