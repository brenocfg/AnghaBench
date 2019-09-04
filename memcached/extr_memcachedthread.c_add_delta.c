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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  enum delta_result_type { ____Placeholder_delta_result_type } delta_result_type ;
typedef  int /*<<< orphan*/  conn ;

/* Variables and functions */
 int do_add_delta (int /*<<< orphan*/ *,char const*,size_t const,int,int /*<<< orphan*/  const,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash (char const*,size_t const) ; 
 int /*<<< orphan*/  item_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_unlock (int /*<<< orphan*/ ) ; 

enum delta_result_type add_delta(conn *c, const char *key,
                                 const size_t nkey, bool incr,
                                 const int64_t delta, char *buf,
                                 uint64_t *cas) {
    enum delta_result_type ret;
    uint32_t hv;

    hv = hash(key, nkey);
    item_lock(hv);
    ret = do_add_delta(c, key, nkey, incr, delta, buf, cas, hv);
    item_unlock(hv);
    return ret;
}