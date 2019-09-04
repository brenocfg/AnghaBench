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
struct metapage {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _metapage_homeok (struct metapage*) ; 
 int /*<<< orphan*/  hold_metapage (struct metapage*) ; 
 int /*<<< orphan*/  put_metapage (struct metapage*) ; 

__attribute__((used)) static inline void metapage_homeok(struct metapage *mp)
{
	hold_metapage(mp);
	_metapage_homeok(mp);
	put_metapage(mp);
}