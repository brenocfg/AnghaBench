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
struct cdb {int /*<<< orphan*/ * fp; } ;
typedef  int /*<<< orphan*/  php_stream ;

/* Variables and functions */
 int /*<<< orphan*/  cdb_findstart (struct cdb*) ; 
 int /*<<< orphan*/  cdb_free (struct cdb*) ; 

void cdb_init(struct cdb *c, php_stream *fp)
{
	cdb_free(c);
	cdb_findstart(c);
	c->fp = fp;
}