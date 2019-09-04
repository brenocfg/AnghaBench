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
struct cdb {int dummy; } ;

/* Variables and functions */
 int cdb_findnext (struct cdb*,char*,unsigned int) ; 
 int /*<<< orphan*/  cdb_findstart (struct cdb*) ; 

int cdb_find(struct cdb *c, char *key, unsigned int len)
{
	cdb_findstart(c);
	return cdb_findnext(c, key, len);
}