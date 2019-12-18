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
struct doall_md {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* fn ) (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/ * data; scalar_t__ alias; } ;
typedef  TYPE_1__ OBJ_NAME ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_all_md_fn(const OBJ_NAME *nm, void *arg)
{
    struct doall_md *dc = arg;
    if (nm->alias)
        dc->fn(NULL, nm->name, nm->data, dc->arg);
    else
        dc->fn((const EVP_MD *)nm->data, nm->name, NULL, dc->arg);
}