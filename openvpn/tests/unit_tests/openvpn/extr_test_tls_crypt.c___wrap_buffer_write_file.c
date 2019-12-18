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
struct buffer {int dummy; } ;

/* Variables and functions */
 char* BSTR (struct buffer const*) ; 
 int /*<<< orphan*/  check_expected (char const*) ; 
 int mock () ; 

bool
__wrap_buffer_write_file(const char *filename, const struct buffer *buf)
{
    const char *pem = BSTR(buf);
    check_expected(filename);
    check_expected(pem);

    return mock();
}