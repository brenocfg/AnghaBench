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
typedef  int /*<<< orphan*/  X509_EXTENSION ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_get_mem_data (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 int /*<<< orphan*/  BIO_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_str_eq (char*,char const*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509V3_EXT_DEFAULT ; 
 int /*<<< orphan*/  X509V3_EXT_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int compare_extension_printout(X509_EXTENSION *extension,
                                      const char *expected_output)
{
    BIO *text_buffer = NULL;
    char *actual_output = NULL;
    int result = 0;

    if (!TEST_ptr(text_buffer = BIO_new(BIO_s_mem()))
            || !TEST_true(X509V3_EXT_print(text_buffer, extension,
                                           X509V3_EXT_DEFAULT, 0)))
        goto end;

    /* Append \0 because we're about to use the buffer contents as a string. */
    if (!TEST_true(BIO_write(text_buffer, "\0", 1)))
        goto end;

    BIO_get_mem_data(text_buffer, &actual_output);
    if (!TEST_str_eq(actual_output, expected_output))
        goto end;

    result = 1;

end:
    BIO_free(text_buffer);
    return result;
}