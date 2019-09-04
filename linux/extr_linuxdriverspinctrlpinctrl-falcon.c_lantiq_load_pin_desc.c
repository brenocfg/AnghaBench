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
struct pinctrl_pin_desc {int number; char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PINS ; 
 char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int* pad_count ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void lantiq_load_pin_desc(struct pinctrl_pin_desc *d, int bank, int len)
{
	int base = bank * PINS;
	int i;

	for (i = 0; i < len; i++) {
		/* strlen("ioXYZ") + 1 = 6 */
		char *name = kzalloc(6, GFP_KERNEL);

		snprintf(name, 6, "io%d", base + i);
		d[i].number = base + i;
		d[i].name = name;
	}
	pad_count[bank] = len;
}