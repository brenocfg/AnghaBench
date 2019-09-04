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
typedef  int /*<<< orphan*/  u8 ;
struct key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct key* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct key *request_trusted_key(const char *trusted_desc,
					      const u8 **master_key,
					      size_t *master_keylen)
{
	return ERR_PTR(-EOPNOTSUPP);
}