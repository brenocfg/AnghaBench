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
struct multi_transaction {size_t size; } ;
struct file {struct multi_transaction* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 size_t MULTI_TRANSACTION_LIMIT ; 
 int /*<<< orphan*/  multi_transaction_lock ; 
 int /*<<< orphan*/  put_multi_transaction (struct multi_transaction*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void multi_transaction_set(struct file *file,
				  struct multi_transaction *new, size_t n)
{
	struct multi_transaction *old;

	AA_BUG(n > MULTI_TRANSACTION_LIMIT);

	new->size = n;
	spin_lock(&multi_transaction_lock);
	old = (struct multi_transaction *) file->private_data;
	file->private_data = new;
	spin_unlock(&multi_transaction_lock);
	put_multi_transaction(old);
}