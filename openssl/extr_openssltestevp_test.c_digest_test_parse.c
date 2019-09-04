#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  input; int /*<<< orphan*/  output_len; int /*<<< orphan*/  output; } ;
struct TYPE_4__ {TYPE_2__* data; } ;
typedef  TYPE_1__ EVP_TEST ;
typedef  TYPE_2__ DIGEST_DATA ;

/* Variables and functions */
 int evp_test_buffer_append (char const*,int /*<<< orphan*/ *) ; 
 int evp_test_buffer_ncopy (char const*,int /*<<< orphan*/ ) ; 
 int evp_test_buffer_set_count (char const*,int /*<<< orphan*/ ) ; 
 int parse_bin (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int digest_test_parse(EVP_TEST *t,
                             const char *keyword, const char *value)
{
    DIGEST_DATA *mdata = t->data;

    if (strcmp(keyword, "Input") == 0)
        return evp_test_buffer_append(value, &mdata->input);
    if (strcmp(keyword, "Output") == 0)
        return parse_bin(value, &mdata->output, &mdata->output_len);
    if (strcmp(keyword, "Count") == 0)
        return evp_test_buffer_set_count(value, mdata->input);
    if (strcmp(keyword, "Ncopy") == 0)
        return evp_test_buffer_ncopy(value, mdata->input);
    return 0;
}