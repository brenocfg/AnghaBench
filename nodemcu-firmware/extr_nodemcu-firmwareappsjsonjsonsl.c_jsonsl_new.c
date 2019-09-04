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
struct jsonsl_st {int dummy; } ;
typedef  struct jsonsl_st* jsonsl_t ;

/* Variables and functions */
 scalar_t__ calloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonsl_get_size (int) ; 
 int /*<<< orphan*/  jsonsl_init (struct jsonsl_st*,int) ; 

jsonsl_t jsonsl_new(int nlevels)
{
    struct jsonsl_st *jsn = (struct jsonsl_st *)
            calloc(1, jsonsl_get_size(nlevels));

    if (jsn) {
      jsonsl_init(jsn, nlevels);
    }
    return jsn;
}