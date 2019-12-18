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
struct stringpool {char* start; int alloced; size_t used; } ;
typedef  int /*<<< orphan*/  buf4096 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int s (char*) ; 
 int /*<<< orphan*/  ss (char*) ; 
 char* stringpool_add (struct stringpool*,char*,...) ; 
 int /*<<< orphan*/  stringpool_init (struct stringpool*) ; 

int main() {
	char buf4096[4096];
	struct stringpool sp;
	stringpool_init(&sp);
	char *r;
	size_t pos = 0;
	r = stringpool_add(&sp, ss("AAAAA"));
	assert(r == sp.start);
	
	pos += s("AAAAA");
	assert(sp.alloced == 4096);
	assert(sp.used == pos);
	
	r = stringpool_add(&sp, buf4096, sizeof(buf4096));
	assert(r == sp.start + pos);
	
	pos += sizeof(buf4096);
	assert(sp.alloced == 4096 * 2);
	assert(sp.used == pos);
	
	r = stringpool_add(&sp, buf4096, 4096 - s("AAAAA"));
	assert(r == sp.start + pos);
	pos += 4096 - s("AAAAA");
	assert(pos == 4096 * 2);

	assert(sp.alloced == 4096 * 2);
	assert(sp.used == pos);
	
	
	
	return 0;
	
}