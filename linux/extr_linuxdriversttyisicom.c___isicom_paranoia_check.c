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
struct isi_port {scalar_t__ magic; } ;

/* Variables and functions */
 scalar_t__ ISICOM_MAGIC ; 
 int /*<<< orphan*/  pr_warn (char*,char*,char const*) ; 

__attribute__((used)) static inline int __isicom_paranoia_check(struct isi_port const *port,
	char *name, const char *routine)
{
	if (!port) {
		pr_warn("Warning: bad isicom magic for dev %s in %s\n",
			name, routine);
		return 1;
	}
	if (port->magic != ISICOM_MAGIC) {
		pr_warn("Warning: NULL isicom port for dev %s in %s\n",
			name, routine);
		return 1;
	}

	return 0;
}