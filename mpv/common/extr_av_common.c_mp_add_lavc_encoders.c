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
struct mp_decoder_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVMEDIA_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  add_codecs (struct mp_decoder_list*,int /*<<< orphan*/ ,int) ; 

void mp_add_lavc_encoders(struct mp_decoder_list *list)
{
    add_codecs(list, AVMEDIA_TYPE_UNKNOWN, false);
}