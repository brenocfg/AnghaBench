#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int argc; char** argv; } ;

/* Variables and functions */
 char** bmalloc (int) ; 
 TYPE_1__ cmdline_args ; 
 int /*<<< orphan*/  memcpy (char*,char const* const,size_t) ; 
 int strlen (char const* const) ; 

void obs_set_cmdline_args(int argc, const char *const *argv)
{
	char *data;
	size_t len;
	int i;

	/* Once argc is set (non-zero) we shouldn't call again */
	if (cmdline_args.argc)
		return;

	cmdline_args.argc = argc;

	/* Safely copy over argv */
	len = 0;
	for (i = 0; i < argc; i++)
		len += strlen(argv[i]) + 1;

	cmdline_args.argv = bmalloc(sizeof(char *) * (argc + 1) + len);
	data = (char *)cmdline_args.argv + sizeof(char *) * (argc + 1);

	for (i = 0; i < argc; i++) {
		cmdline_args.argv[i] = data;
		len = strlen(argv[i]) + 1;
		memcpy(data, argv[i], len);
		data += len;
	}

	cmdline_args.argv[argc] = NULL;
}