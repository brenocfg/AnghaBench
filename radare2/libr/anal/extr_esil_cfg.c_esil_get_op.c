#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ops; } ;
typedef  int /*<<< orphan*/  RAnalEsilOp ;
typedef  TYPE_1__ RAnalEsil ;

/* Variables and functions */
 int /*<<< orphan*/  r_return_val_if_fail (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdb_hash (char const*) ; 
 char* sdb_itoa (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ sdb_num_get (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 

RAnalEsilOp *esil_get_op (RAnalEsil *esil, const char *op) {
	r_return_val_if_fail (op && strlen (op) && esil && esil->ops, NULL);
	char t[128];
	char *h = sdb_itoa (sdb_hash (op), t, 16);
	return (RAnalEsilOp *)(size_t)sdb_num_get (esil->ops, h, 0);
}