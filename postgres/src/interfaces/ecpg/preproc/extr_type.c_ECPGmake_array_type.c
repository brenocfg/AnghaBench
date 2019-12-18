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
struct TYPE_2__ {struct ECPGtype* element; } ;
struct ECPGtype {TYPE_1__ u; } ;

/* Variables and functions */
 struct ECPGtype* ECPGmake_simple_type (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECPGt_array ; 

struct ECPGtype *
ECPGmake_array_type(struct ECPGtype *type, char *size)
{
	struct ECPGtype *ne = ECPGmake_simple_type(ECPGt_array, size, 0);

	ne->u.element = type;

	return ne;
}