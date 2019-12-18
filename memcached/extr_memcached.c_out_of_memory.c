#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  error_prefix ;
struct TYPE_5__ {scalar_t__ protocol; } ;
typedef  TYPE_1__ conn ;

/* Variables and functions */
 int /*<<< orphan*/  PROTOCOL_BINARY_RESPONSE_ENOMEM ; 
 scalar_t__ binary_prot ; 
 int /*<<< orphan*/  out_string (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,int const) ; 
 int /*<<< orphan*/  write_bin_error (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void out_of_memory(conn *c, char *ascii_error) {
    const static char error_prefix[] = "SERVER_ERROR ";
    const static int error_prefix_len = sizeof(error_prefix) - 1;

    if (c->protocol == binary_prot) {
        /* Strip off the generic error prefix; it's irrelevant in binary */
        if (!strncmp(ascii_error, error_prefix, error_prefix_len)) {
            ascii_error += error_prefix_len;
        }
        write_bin_error(c, PROTOCOL_BINARY_RESPONSE_ENOMEM, ascii_error, 0);
    } else {
        out_string(c, ascii_error);
    }
}