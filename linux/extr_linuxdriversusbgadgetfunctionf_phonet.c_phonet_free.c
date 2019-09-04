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
struct usb_function {int dummy; } ;
struct f_phonet {int dummy; } ;

/* Variables and functions */
 struct f_phonet* func_to_pn (struct usb_function*) ; 
 int /*<<< orphan*/  kfree (struct f_phonet*) ; 

__attribute__((used)) static void phonet_free(struct usb_function *f)
{
	struct f_phonet *phonet;

	phonet = func_to_pn(f);
	kfree(phonet);
}