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
struct index_cases_st {scalar_t__ n; int /*<<< orphan*/  v; } ;
struct doall_st {int res; size_t num_cases; int /*<<< orphan*/  sa; struct index_cases_st* cases; } ;
typedef  scalar_t__ ossl_uintmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_error (char*,scalar_t__,char*) ; 
 int /*<<< orphan*/  ossl_sa_char_set (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void leaf_delete(ossl_uintmax_t n, char *value, void *arg)
{
    struct doall_st *doall_data = (struct doall_st *)arg;
    const struct index_cases_st *cases = doall_data->cases;
    size_t i;

    doall_data->res = 0;
    for (i = 0; i < doall_data->num_cases; i++)
        if (n == cases[i].n && strcmp(value, cases[i].v) == 0) {
            doall_data->res = 1;
            ossl_sa_char_set(doall_data->sa, n, NULL);
            return;
        }
    TEST_error("Index %ju with value %s not found", n, value);
}