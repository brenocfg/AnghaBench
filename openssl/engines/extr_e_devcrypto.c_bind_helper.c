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
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  bind_devcrypto (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_devcrypto () ; 
 int /*<<< orphan*/  engine_devcrypto_id ; 
 int /*<<< orphan*/  open_devcrypto () ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bind_helper(ENGINE *e, const char *id)
{
    if ((id && (strcmp(id, engine_devcrypto_id) != 0))
        || !open_devcrypto())
        return 0;
    if (!bind_devcrypto(e)) {
        close_devcrypto();
        return 0;
    }
    return 1;
}