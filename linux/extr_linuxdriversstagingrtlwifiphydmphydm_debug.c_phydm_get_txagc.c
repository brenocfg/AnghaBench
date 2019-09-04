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
typedef  int u32 ;
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_RF_PATH_A ; 
 int /*<<< orphan*/  ODM_RF_PATH_B ; 
 int /*<<< orphan*/  ODM_RF_PATH_C ; 
 int /*<<< orphan*/  ODM_RF_PATH_D ; 
 int /*<<< orphan*/  PHYDM_SNPRINTF (char*,int,char*,char*) ; 
 int /*<<< orphan*/  phydm_get_per_path_txagc (struct phy_dm_struct*,int /*<<< orphan*/ ,int*,char*,int*) ; 

__attribute__((used)) static void phydm_get_txagc(void *dm_void, u32 *_used, char *output,
			    u32 *_out_len)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u32 used = *_used;
	u32 out_len = *_out_len;

	/* path-A */
	PHYDM_SNPRINTF(output + used, out_len - used, "%-35s\n",
		       "path-A====================");
	phydm_get_per_path_txagc(dm, ODM_RF_PATH_A, _used, output, _out_len);

	/* path-B */
	PHYDM_SNPRINTF(output + used, out_len - used, "\n%-35s\n",
		       "path-B====================");
	phydm_get_per_path_txagc(dm, ODM_RF_PATH_B, _used, output, _out_len);

	/* path-C */
	PHYDM_SNPRINTF(output + used, out_len - used, "\n%-35s\n",
		       "path-C====================");
	phydm_get_per_path_txagc(dm, ODM_RF_PATH_C, _used, output, _out_len);

	/* path-D */
	PHYDM_SNPRINTF(output + used, out_len - used, "\n%-35s\n",
		       "path-D====================");
	phydm_get_per_path_txagc(dm, ODM_RF_PATH_D, _used, output, _out_len);
}