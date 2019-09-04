#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_3__ {void*** DeltaSwingTableIdx_5GB_N; void*** DeltaSwingTableIdx_5GB_P; void*** DeltaSwingTableIdx_5GA_N; void*** DeltaSwingTableIdx_5GA_P; void** DeltaSwingTableIdx_2GB_N; void** DeltaSwingTableIdx_2GB_P; void** DeltaSwingTableIdx_2GA_N; void** DeltaSwingTableIdx_2GA_P; void** DeltaSwingTableIdx_2GCCKB_N; void** DeltaSwingTableIdx_2GCCKB_P; void** DeltaSwingTableIdx_2GCCKA_N; void** DeltaSwingTableIdx_2GCCKA_P; } ;
struct TYPE_4__ {TYPE_1__ RFCalibrateInfo; } ;
struct hal_com_data {TYPE_2__ odmpriv; } ;
struct adapter {int dummy; } ;
typedef  TYPE_1__* PODM_RF_CAL_T ;
typedef  TYPE_2__* PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*) ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  sscanf (char*,char*,scalar_t__*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static void initDeltaSwingIndexTables(
	struct adapter *Adapter,
	char *Band,
	char *Path,
	char *Sign,
	char *Channel,
	char *Rate,
	char *Data
)
{
	#define STR_EQUAL_5G(_band, _path, _sign, _rate, _chnl) \
		((strcmp(Band, _band) == 0) && (strcmp(Path, _path) == 0) && (strcmp(Sign, _sign) == 0) &&\
		(strcmp(Rate, _rate) == 0) && (strcmp(Channel, _chnl) == 0)\
	)
	#define STR_EQUAL_2G(_band, _path, _sign, _rate) \
		((strcmp(Band, _band) == 0) && (strcmp(Path, _path) == 0) && (strcmp(Sign, _sign) == 0) &&\
		(strcmp(Rate, _rate) == 0)\
	)

	#define STORE_SWING_TABLE(_array, _iteratedIdx) \
		for (token = strsep(&Data, delim); token != NULL; token = strsep(&Data, delim)) {\
			sscanf(token, "%d", &idx);\
			_array[_iteratedIdx++] = (u8)idx;\
		} \

	struct hal_com_data	*pHalData = GET_HAL_DATA(Adapter);
	PDM_ODM_T pDM_Odm = &pHalData->odmpriv;
	PODM_RF_CAL_T pRFCalibrateInfo = &(pDM_Odm->RFCalibrateInfo);
	u32 j = 0;
	char *token;
	char delim[] = ",";
	u32 idx = 0;

	/* DBG_871X("===>initDeltaSwingIndexTables(): Band: %s;\nPath: %s;\nSign: %s;\nChannel: %s;\nRate: %s;\n, Data: %s;\n", */
	/*	Band, Path, Sign, Channel, Rate, Data); */

	if (STR_EQUAL_2G("2G", "A", "+", "CCK")) {
		STORE_SWING_TABLE(pRFCalibrateInfo->DeltaSwingTableIdx_2GCCKA_P, j);
	} else if (STR_EQUAL_2G("2G", "A", "-", "CCK")) {
		STORE_SWING_TABLE(pRFCalibrateInfo->DeltaSwingTableIdx_2GCCKA_N, j);
	} else if (STR_EQUAL_2G("2G", "B", "+", "CCK")) {
		STORE_SWING_TABLE(pRFCalibrateInfo->DeltaSwingTableIdx_2GCCKB_P, j);
	} else if (STR_EQUAL_2G("2G", "B", "-", "CCK")) {
		STORE_SWING_TABLE(pRFCalibrateInfo->DeltaSwingTableIdx_2GCCKB_N, j);
	} else if (STR_EQUAL_2G("2G", "A", "+", "ALL")) {
		STORE_SWING_TABLE(pRFCalibrateInfo->DeltaSwingTableIdx_2GA_P, j);
	} else if (STR_EQUAL_2G("2G", "A", "-", "ALL")) {
		STORE_SWING_TABLE(pRFCalibrateInfo->DeltaSwingTableIdx_2GA_N, j);
	} else if (STR_EQUAL_2G("2G", "B", "+", "ALL")) {
		STORE_SWING_TABLE(pRFCalibrateInfo->DeltaSwingTableIdx_2GB_P, j);
	} else if (STR_EQUAL_2G("2G", "B", "-", "ALL")) {
		STORE_SWING_TABLE(pRFCalibrateInfo->DeltaSwingTableIdx_2GB_N, j);
	} else if (STR_EQUAL_5G("5G", "A", "+", "ALL", "0")) {
		STORE_SWING_TABLE(pRFCalibrateInfo->DeltaSwingTableIdx_5GA_P[0], j);
	} else if (STR_EQUAL_5G("5G", "A", "-", "ALL", "0")) {
		STORE_SWING_TABLE(pRFCalibrateInfo->DeltaSwingTableIdx_5GA_N[0], j);
	} else if (STR_EQUAL_5G("5G", "B", "+", "ALL", "0")) {
		STORE_SWING_TABLE(pRFCalibrateInfo->DeltaSwingTableIdx_5GB_P[0], j);
	} else if (STR_EQUAL_5G("5G", "B", "-", "ALL", "0")) {
		STORE_SWING_TABLE(pRFCalibrateInfo->DeltaSwingTableIdx_5GB_N[0], j);
	} else if (STR_EQUAL_5G("5G", "A", "+", "ALL", "1")) {
		STORE_SWING_TABLE(pRFCalibrateInfo->DeltaSwingTableIdx_5GA_P[1], j);
	} else if (STR_EQUAL_5G("5G", "A", "-", "ALL", "1")) {
		STORE_SWING_TABLE(pRFCalibrateInfo->DeltaSwingTableIdx_5GA_N[1], j);
	} else if (STR_EQUAL_5G("5G", "B", "+", "ALL", "1")) {
		STORE_SWING_TABLE(pRFCalibrateInfo->DeltaSwingTableIdx_5GB_P[1], j);
	} else if (STR_EQUAL_5G("5G", "B", "-", "ALL", "1")) {
		STORE_SWING_TABLE(pRFCalibrateInfo->DeltaSwingTableIdx_5GB_N[1], j);
	} else if (STR_EQUAL_5G("5G", "A", "+", "ALL", "2")) {
		STORE_SWING_TABLE(pRFCalibrateInfo->DeltaSwingTableIdx_5GA_P[2], j);
	} else if (STR_EQUAL_5G("5G", "A", "-", "ALL", "2")) {
		STORE_SWING_TABLE(pRFCalibrateInfo->DeltaSwingTableIdx_5GA_N[2], j);
	} else if (STR_EQUAL_5G("5G", "B", "+", "ALL", "2")) {
		STORE_SWING_TABLE(pRFCalibrateInfo->DeltaSwingTableIdx_5GB_P[2], j);
	} else if (STR_EQUAL_5G("5G", "B", "-", "ALL", "2")) {
		STORE_SWING_TABLE(pRFCalibrateInfo->DeltaSwingTableIdx_5GB_N[2], j);
	} else if (STR_EQUAL_5G("5G", "A", "+", "ALL", "3")) {
		STORE_SWING_TABLE(pRFCalibrateInfo->DeltaSwingTableIdx_5GA_P[3], j);
	} else if (STR_EQUAL_5G("5G", "A", "-", "ALL", "3")) {
		STORE_SWING_TABLE(pRFCalibrateInfo->DeltaSwingTableIdx_5GA_N[3], j);
	} else if (STR_EQUAL_5G("5G", "B", "+", "ALL", "3")) {
		STORE_SWING_TABLE(pRFCalibrateInfo->DeltaSwingTableIdx_5GB_P[3], j);
	} else if (STR_EQUAL_5G("5G", "B", "-", "ALL", "3")) {
		STORE_SWING_TABLE(pRFCalibrateInfo->DeltaSwingTableIdx_5GB_N[3], j);
	} else
		DBG_871X("===>initDeltaSwingIndexTables(): The input is invalid!!\n");
}