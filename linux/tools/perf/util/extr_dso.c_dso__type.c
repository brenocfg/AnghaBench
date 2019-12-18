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
struct machine {int dummy; } ;
struct dso {int dummy; } ;
typedef  enum dso_type { ____Placeholder_dso_type } dso_type ;

/* Variables and functions */
 int DSO__TYPE_UNKNOWN ; 
 int dso__data_get_fd (struct dso*,struct machine*) ; 
 int /*<<< orphan*/  dso__data_put_fd (struct dso*) ; 
 int dso__type_fd (int) ; 

enum dso_type dso__type(struct dso *dso, struct machine *machine)
{
	int fd;
	enum dso_type type = DSO__TYPE_UNKNOWN;

	fd = dso__data_get_fd(dso, machine);
	if (fd >= 0) {
		type = dso__type_fd(fd);
		dso__data_put_fd(dso);
	}

	return type;
}