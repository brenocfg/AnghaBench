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
typedef  int uint8_t ;
struct rrdengine_worker_config {int dummy; } ;
struct extent_io_descriptor {int dummy; } ;

/* Variables and functions */
#define  STORE_DATA 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  commit_data_extent (struct rrdengine_worker_config*,struct extent_io_descriptor*) ; 

__attribute__((used)) static void do_commit_transaction(struct rrdengine_worker_config* wc, uint8_t type, void *data)
{
    switch (type) {
    case STORE_DATA:
        commit_data_extent(wc, (struct extent_io_descriptor *)data);
        break;
    default:
        assert(type == STORE_DATA);
        break;
    }
}