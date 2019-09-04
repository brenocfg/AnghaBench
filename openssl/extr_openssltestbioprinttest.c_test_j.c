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
struct TYPE_3__ {int /*<<< orphan*/  expected; int /*<<< orphan*/  value; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ j_data ;
typedef  int /*<<< orphan*/  bio_buf ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_snprintf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_str_eq (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* jf_data ; 

__attribute__((used)) static int test_j(int i)
{
    const j_data *data = &jf_data[i];
    char bio_buf[80];

    BIO_snprintf(bio_buf, sizeof(bio_buf) - 1, data->format, data->value);
    if (!TEST_str_eq(bio_buf, data->expected))
        return 0;
    return 1;
}