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
typedef  int ssize_t ;
typedef  int off_t ;
struct TYPE_3__ {int (* read ) (TYPE_1__*,char*,int) ;} ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* con ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (scalar_t__) ; 
 int stub1 (TYPE_1__*,char*,int) ; 

__attribute__((used)) static void read_ascii_response(char *buffer, size_t size) {
    off_t offset = 0;
    bool need_more = true;
    do {
        ssize_t nr = con->read(con, buffer + offset, 1);
        if (nr == -1) {
            if (errno != EINTR) {
                fprintf(stderr, "Failed to read: %s\n", strerror(errno));
                abort();
            }
        } else {
            assert(nr == 1);
            if (buffer[offset] == '\n') {
                need_more = false;
                buffer[offset + 1] = '\0';
            }
            offset += nr;
            assert(offset + 1 < size);
        }
    } while (need_more);
}