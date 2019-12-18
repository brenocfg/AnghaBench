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
struct gpiochip_info {int lines; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (struct gpiochip_info*) ; 
 int /*<<< orphan*/  gpio_pin_tests (struct gpiochip_info*,int) ; 
 struct gpiochip_info* list_gpiochip (char*,int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int random () ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 

int main(int argc, char *argv[])
{
	char *prefix;
	int valid;
	struct gpiochip_info *cinfo;
	struct gpiochip_info *current;
	int i;
	int ret;

	if (argc < 3) {
		printf("Usage: %s prefix is_valid", argv[0]);
		exit(EXIT_FAILURE);
	}

	prefix = argv[1];
	valid = strcmp(argv[2], "true") == 0 ? 1 : 0;

	printf("Test gpiochip %s: ", prefix);
	cinfo = list_gpiochip(prefix, &ret);
	if (!cinfo) {
		if (!valid && ret == 0) {
			printf("Invalid test successful\n");
			ret = 0;
			goto out;
		} else {
			ret = -EINVAL;
			goto out;
		}
	} else if (cinfo && !valid) {
		ret = -EINVAL;
		goto out;
	}
	current = cinfo;
	for (i = 0; i < ret; i++) {
		gpio_pin_tests(current, 0);
		gpio_pin_tests(current, current->lines - 1);
		gpio_pin_tests(current, random() % current->lines);
		current++;
	}
	ret = 0;
	printf("successful\n");

out:
	if (ret)
		fprintf(stderr, "gpio<%s> test failed\n", prefix);

	if (cinfo)
		free(cinfo);

	if (ret)
		exit(EXIT_FAILURE);

	return ret;
}