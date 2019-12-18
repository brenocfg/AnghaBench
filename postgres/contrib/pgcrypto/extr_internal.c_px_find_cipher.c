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
struct TYPE_2__ {int /*<<< orphan*/ * (* load ) () ;scalar_t__ name; } ;
typedef  int /*<<< orphan*/  PX_Cipher ;

/* Variables and functions */
 int PXE_NO_CIPHER ; 
 int /*<<< orphan*/  int_aliases ; 
 TYPE_1__* int_ciphers ; 
 char* px_resolve_alias (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 
 int /*<<< orphan*/ * stub1 () ; 

int
px_find_cipher(const char *name, PX_Cipher **res)
{
	int			i;
	PX_Cipher  *c = NULL;

	name = px_resolve_alias(int_aliases, name);

	for (i = 0; int_ciphers[i].name; i++)
		if (strcmp(int_ciphers[i].name, name) == 0)
		{
			c = int_ciphers[i].load();
			break;
		}

	if (c == NULL)
		return PXE_NO_CIPHER;

	*res = c;
	return 0;
}