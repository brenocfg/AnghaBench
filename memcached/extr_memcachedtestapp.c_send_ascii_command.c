#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
typedef  size_t off_t ;
struct TYPE_2__ {int (* write ) (void*,char const*,size_t) ;} ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  abort () ; 
 TYPE_1__* con ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (scalar_t__) ; 
 size_t strlen (char const*) ; 
 int stub1 (void*,char const*,size_t) ; 

__attribute__((used)) static void send_ascii_command(const char *buf) {
    off_t offset = 0;
    const char* ptr = buf;
    size_t len = strlen(buf);

    do {
        ssize_t nw = con->write((void*)con, ptr + offset, len - offset);
        if (nw == -1) {
            if (errno != EINTR) {
                fprintf(stderr, "Failed to write: %s\n", strerror(errno));
                abort();
            }
        } else {
            offset += nw;
        }
    } while (offset < len);
}