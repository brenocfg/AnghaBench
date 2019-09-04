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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  ext_command (char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const*,size_t,void const*,size_t) ; 

__attribute__((used)) static off_t raw_command(char* buf,
                         size_t bufsz,
                         uint8_t cmd,
                         const void* key,
                         size_t keylen,
                         const void* dta,
                         size_t dtalen) {
    /* all of the storage commands use the same command layout */
    return ext_command(buf, bufsz, cmd, NULL, 0, key, keylen, dta, dtalen);
}