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
struct num2name_data_st {size_t idx; char const* name; } ;
typedef  int /*<<< orphan*/  OSSL_NAMEMAP ;

/* Variables and functions */
 int /*<<< orphan*/  do_num2name ; 
 int /*<<< orphan*/  ossl_namemap_doall_names (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,struct num2name_data_st*) ; 

const char *ossl_namemap_num2name(const OSSL_NAMEMAP *namemap, int number,
                                  size_t idx)
{
    struct num2name_data_st data;

    data.idx = idx;
    data.name = NULL;
    ossl_namemap_doall_names(namemap, number, do_num2name, &data);
    return data.name;
}