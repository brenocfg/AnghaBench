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

/* Variables and functions */
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_add_error_data (int,char*) ; 
 int /*<<< orphan*/  ERR_peek_error_data (char const**,int /*<<< orphan*/ *) ; 
 int TEST_str_eq (char const*,char*) ; 

__attribute__((used)) static int vdata_appends(void)
{
    const char *data;

    CRYPTOerr(0, ERR_R_MALLOC_FAILURE);
    ERR_add_error_data(1, "hello ");
    ERR_add_error_data(1, "world");
    ERR_peek_error_data(&data, NULL);
    return TEST_str_eq(data, "hello world");
}