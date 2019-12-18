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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  tmp2 ;

/* Variables and functions */
 int /*<<< orphan*/  RtlCopyMemory (char*,char*,int) ; 

__attribute__((used)) static char* uint64_to_char(uint64_t num, char* buf) {
    char *tmp, tmp2[20];

    if (num == 0) {
        buf[0] = '0';
        return buf + 1;
    }

    tmp = &tmp2[20];
    while (num > 0) {
        tmp--;
        *tmp = (num % 10) + '0';
        num /= 10;
    }

    RtlCopyMemory(buf, tmp, tmp2 + sizeof(tmp2) - tmp);

    return &buf[tmp2 + sizeof(tmp2) - tmp];
}