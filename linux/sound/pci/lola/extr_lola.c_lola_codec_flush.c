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
struct lola {int dummy; } ;

/* Variables and functions */
 int rirb_get_response (struct lola*,unsigned int*,int /*<<< orphan*/ *) ; 

int lola_codec_flush(struct lola *chip)
{
	unsigned int tmp;
	return rirb_get_response(chip, &tmp, NULL);
}