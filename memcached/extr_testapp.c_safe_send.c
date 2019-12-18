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
typedef  int uint8_t ;
typedef  int ssize_t ;
typedef  size_t off_t ;
struct TYPE_3__ {int (* write ) (TYPE_1__*,char const*,size_t) ;} ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* con ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int rand () ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (scalar_t__) ; 
 int stub1 (TYPE_1__*,char const*,size_t) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void safe_send(const void* buf, size_t len, bool hickup)
{
    off_t offset = 0;
    const char* ptr = buf;
#ifdef MESSAGE_DEBUG
    uint8_t val = *ptr;
    assert(val == (uint8_t)0x80);
    fprintf(stderr, "About to send %lu bytes:", (unsigned long)len);
    for (int ii = 0; ii < len; ++ii) {
        if (ii % 4 == 0) {
            fprintf(stderr, "\n   ");
        }
        val = *(ptr + ii);
        fprintf(stderr, " 0x%02x", val);
    }
    fprintf(stderr, "\n");
    usleep(500);
#endif

    do {
        size_t num_bytes = len - offset;
        if (hickup) {
            if (num_bytes > 1024) {
                num_bytes = (rand() % 1023) + 1;
            }
        }
        ssize_t nw = con->write(con, ptr + offset, num_bytes);
        if (nw == -1) {
            if (errno != EINTR) {
                fprintf(stderr, "Failed to write: %s\n", strerror(errno));
                abort();
            }
        } else {
            if (hickup) {
                usleep(100);
            }
            offset += nw;
        }
    } while (offset < len);
}