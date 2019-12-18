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
struct KeynameKeeper {int /*<<< orphan*/  buf; int /*<<< orphan*/  keyLen; int /*<<< orphan*/  keyName; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CRYPT_InitializeKeynameKeeper(struct KeynameKeeper *keeper)
{
    keeper->keyName = keeper->buf;
    keeper->keyLen = ARRAY_SIZE(keeper->buf);
}