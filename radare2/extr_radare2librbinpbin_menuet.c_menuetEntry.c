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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;

/* Variables and functions */
 int MENUET_VERSION (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  UT64_MAX ; 
 int /*<<< orphan*/  r_read_ble32 (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static ut64 menuetEntry(const ut8 *buf, int buf_size) {
	switch (MENUET_VERSION(buf)) {
	case '0': return r_read_ble32 (buf + 12, false);
	case '1': return r_read_ble32 (buf + 12, false);
	case '2': return r_read_ble32 (buf + 44, false);
	}
	return UT64_MAX;
}