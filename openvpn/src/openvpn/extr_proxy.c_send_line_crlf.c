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
typedef  int /*<<< orphan*/  socket_descriptor_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BSTR (struct buffer*) ; 
 struct buffer alloc_buf (int) ; 
 int /*<<< orphan*/  buf_write (struct buffer*,char const*,int) ; 
 int /*<<< orphan*/  free_buf (struct buffer*) ; 
 int send_line (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

__attribute__((used)) static bool
send_line_crlf(socket_descriptor_t sd,
               const char *src)
{
    bool ret;

    struct buffer buf = alloc_buf(strlen(src) + 3);
    ASSERT(buf_write(&buf, src, strlen(src)));
    ASSERT(buf_write(&buf, "\r\n", 3));
    ret = send_line(sd, BSTR(&buf));
    free_buf(&buf);
    return ret;
}