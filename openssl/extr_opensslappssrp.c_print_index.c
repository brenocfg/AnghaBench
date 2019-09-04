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
typedef  int /*<<< orphan*/  CA_DB ;

/* Variables and functions */
 int /*<<< orphan*/  print_entry (int /*<<< orphan*/ *,int,int,char*) ; 

__attribute__((used)) static void print_index(CA_DB *db, int indexindex, int verbose)
{
    print_entry(db, indexindex, verbose, "g N entry");
}