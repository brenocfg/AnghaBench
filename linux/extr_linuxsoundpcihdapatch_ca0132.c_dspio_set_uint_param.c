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

/* Variables and functions */
 int dspio_set_param (struct hda_codec*,int,int,int,unsigned int const*,int) ; 

__attribute__((used)) static int dspio_set_uint_param(struct hda_codec *codec, int mod_id,
			int req, const unsigned int data)
{
	return dspio_set_param(codec, mod_id, 0x20, req, &data,
			sizeof(unsigned int));
}