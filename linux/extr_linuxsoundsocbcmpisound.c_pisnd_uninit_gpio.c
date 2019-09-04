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
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct gpio_desc***) ; 
 struct gpio_desc* button ; 
 int /*<<< orphan*/  gpiod_put (struct gpio_desc*) ; 
 int /*<<< orphan*/  gpiod_unexport (struct gpio_desc*) ; 
 struct gpio_desc* osr0 ; 
 struct gpio_desc* osr1 ; 
 struct gpio_desc* osr2 ; 
 int /*<<< orphan*/  printd (char*,int) ; 
 struct gpio_desc* reset ; 

__attribute__((used)) static int pisnd_uninit_gpio(void)
{
	int i;

	struct gpio_desc **gpios[] = {
		&osr0, &osr1, &osr2, &reset, &button,
	};

	gpiod_unexport(button);

	for (i = 0; i < ARRAY_SIZE(gpios); ++i) {
		if (*gpios[i] == NULL) {
			printd("weird, GPIO[%d] is NULL already\n", i);
			continue;
		}

		gpiod_put(*gpios[i]);
		*gpios[i] = NULL;
	}

	return 0;
}