#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  root; } ;
struct TYPE_9__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
struct TYPE_10__ {TYPE_1__ binary; } ;
struct TYPE_11__ {TYPE_2__ val; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ JsonbValue ;
typedef  TYPE_4__ Jsonb ;

/* Variables and functions */
 int /*<<< orphan*/  VARSIZE_ANY_EXHDR (TYPE_4__*) ; 
 int /*<<< orphan*/  jbvBinary ; 

__attribute__((used)) static JsonbValue *
JsonbInitBinary(JsonbValue *jbv, Jsonb *jb)
{
	jbv->type = jbvBinary;
	jbv->val.binary.data = &jb->root;
	jbv->val.binary.len = VARSIZE_ANY_EXHDR(jb);

	return jbv;
}