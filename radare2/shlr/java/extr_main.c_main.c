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
typedef  int /*<<< orphan*/  Sdb ;
typedef  int /*<<< orphan*/  RBinJavaObj ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_bin_java_new (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sdb_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int main() {
	Sdb *kv = sdb_new(NULL, NULL, 0);
	RBinJavaObj *o = r_bin_java_new ("/tmp/CON.class", 0, kv);
	printf ("Hello World %p\n", o);
	return 0;
}