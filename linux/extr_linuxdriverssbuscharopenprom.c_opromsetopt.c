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
struct openpromio {char* oprom_array; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int of_set_property (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  options_node ; 
 int strlen (char*) ; 

__attribute__((used)) static int opromsetopt(struct device_node *dp, struct openpromio *op, int bufsize)
{
	char *buf = op->oprom_array + strlen(op->oprom_array) + 1;
	int len = op->oprom_array + bufsize - buf;

	return of_set_property(options_node, op->oprom_array, buf, len);
}