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
typedef  int /*<<< orphan*/  u16 ;
struct hermes {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int HERMES_READ_RECORD (struct hermes*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int hermes_read_wordrec(struct hermes *hw, int bap, u16 rid,
				      u16 *word)
{
	__le16 rec;
	int err;

	err = HERMES_READ_RECORD(hw, bap, rid, &rec);
	*word = le16_to_cpu(rec);
	return err;
}