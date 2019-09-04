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
struct o2net_sock_container {int /*<<< orphan*/  sc_kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_kref_release ; 
 int /*<<< orphan*/  sclog (struct o2net_sock_container*,char*) ; 

__attribute__((used)) static void sc_put(struct o2net_sock_container *sc)
{
	sclog(sc, "put\n");
	kref_put(&sc->sc_kref, sc_kref_release);
}