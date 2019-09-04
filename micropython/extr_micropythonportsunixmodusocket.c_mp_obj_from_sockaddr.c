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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  mp_obj_new_bytes (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline mp_obj_t mp_obj_from_sockaddr(const struct sockaddr *addr, socklen_t len) {
    return mp_obj_new_bytes((const byte *)addr, len);
}