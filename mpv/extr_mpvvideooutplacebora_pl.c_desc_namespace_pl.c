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
struct ra {int dummy; } ;
typedef  enum ra_vartype { ____Placeholder_ra_vartype } ra_vartype ;

/* Variables and functions */
 int /*<<< orphan*/ * desc_type ; 
 int /*<<< orphan*/  get_gpu (struct ra*) ; 
 int pl_desc_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int desc_namespace_pl(struct ra *ra, enum ra_vartype type)
{
    return pl_desc_namespace(get_gpu(ra), desc_type[type]);
}