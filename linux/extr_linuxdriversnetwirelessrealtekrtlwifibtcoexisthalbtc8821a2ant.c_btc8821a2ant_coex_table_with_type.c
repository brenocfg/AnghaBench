#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct btc_coexist {int dummy; } ;
struct TYPE_2__ {int coex_table_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  btc8821a2ant_coex_table (struct btc_coexist*,int,int,int,int,int) ; 
 TYPE_1__* coex_sta ; 

__attribute__((used)) static void btc8821a2ant_coex_table_with_type(struct btc_coexist *btcoexist,
					      bool force_exec, u8 type)
{
	coex_sta->coex_table_type = type;

	switch (type) {
	case 0:
		btc8821a2ant_coex_table(btcoexist, force_exec, 0x55555555,
					0x55555555, 0xffffff, 0x3);
		break;
	case 1:
		btc8821a2ant_coex_table(btcoexist, force_exec, 0x55555555,
					0x5afa5afa, 0xffffff, 0x3);
		break;
	case 2:
		btc8821a2ant_coex_table(btcoexist, force_exec, 0x5ada5ada,
					0x5ada5ada, 0xffffff, 0x3);
		break;
	case 3:
		btc8821a2ant_coex_table(btcoexist, force_exec, 0xaaaaaaaa,
					0xaaaaaaaa, 0xffffff, 0x3);
		break;
	case 4:
		btc8821a2ant_coex_table(btcoexist, force_exec, 0xffffffff,
					0xffffffff, 0xffffff, 0x3);
		break;
	case 5:
		btc8821a2ant_coex_table(btcoexist, force_exec, 0x5fff5fff,
					0x5fff5fff, 0xffffff, 0x3);
		break;
	case 6:
		btc8821a2ant_coex_table(btcoexist, force_exec, 0x55ff55ff,
					0x5a5a5a5a, 0xffffff, 0x3);
		break;
	case 7:
		btc8821a2ant_coex_table(btcoexist, force_exec, 0x55dd55dd,
					0x5ada5ada, 0xffffff, 0x3);
		break;
	case 8:
		btc8821a2ant_coex_table(btcoexist, force_exec, 0x55dd55dd,
					0x5ada5ada, 0xffffff, 0x3);
		break;
	case 9:
		btc8821a2ant_coex_table(btcoexist, force_exec, 0x55dd55dd,
					0x5ada5ada, 0xffffff, 0x3);
		break;
	case 10:
		btc8821a2ant_coex_table(btcoexist, force_exec, 0x55dd55dd,
					0x5ada5ada, 0xffffff, 0x3);
		break;
	case 11:
		btc8821a2ant_coex_table(btcoexist, force_exec, 0x55dd55dd,
					0x5ada5ada, 0xffffff, 0x3);
		break;
	case 12:
		btc8821a2ant_coex_table(btcoexist, force_exec, 0x55dd55dd,
					0x5ada5ada, 0xffffff, 0x3);
		break;
	case 13:
		btc8821a2ant_coex_table(btcoexist, force_exec, 0x5fff5fff,
					0xaaaaaaaa, 0xffffff, 0x3);
		break;
	case 14:
		btc8821a2ant_coex_table(btcoexist, force_exec, 0x5fff5fff,
					0x5ada5ada, 0xffffff, 0x3);
		break;
	case 15:
		btc8821a2ant_coex_table(btcoexist, force_exec, 0x55dd55dd,
					0xaaaaaaaa, 0xffffff, 0x3);
		break;
	case 16:
		btc8821a2ant_coex_table(btcoexist, force_exec, 0x5fdf5fdf,
					0x5fdb5fdb, 0xffffff, 0x3);
		break;
	case 17:
		btc8821a2ant_coex_table(btcoexist, force_exec, 0xfafafafa,
					0xfafafafa, 0xffffff, 0x3);
		break;
	default:
		break;
	}
}