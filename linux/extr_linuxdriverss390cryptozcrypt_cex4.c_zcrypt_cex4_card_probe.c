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
struct zcrypt_card {char* type_string; int online; void* max_exp_bit_length; void* max_mod_size; void* min_mod_size; int /*<<< orphan*/  speed_rating; void* user_space_type; struct ap_card* card; } ;
struct ap_device {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {scalar_t__ device_type; } ;
struct ap_card {struct zcrypt_card* private; TYPE_1__ ap_dev; int /*<<< orphan*/  functions; } ;
typedef  int /*<<< orphan*/  CEX6P_SPEED_IDX ;
typedef  int /*<<< orphan*/  CEX6C_SPEED_IDX ;
typedef  int /*<<< orphan*/  CEX6A_SPEED_IDX ;
typedef  int /*<<< orphan*/  CEX5P_SPEED_IDX ;
typedef  int /*<<< orphan*/  CEX5C_SPEED_IDX ;
typedef  int /*<<< orphan*/  CEX5A_SPEED_IDX ;
typedef  int /*<<< orphan*/  CEX4P_SPEED_IDX ;
typedef  int /*<<< orphan*/  CEX4C_SPEED_IDX ;
typedef  int /*<<< orphan*/  CEX4A_SPEED_IDX ;

/* Variables and functions */
 scalar_t__ AP_DEVICE_TYPE_CEX4 ; 
 scalar_t__ AP_DEVICE_TYPE_CEX5 ; 
 int /*<<< orphan*/  AP_FUNC_ACCEL ; 
 int /*<<< orphan*/  AP_FUNC_COPRO ; 
 int /*<<< orphan*/  AP_FUNC_CRT4K ; 
 int /*<<< orphan*/  AP_FUNC_EP11 ; 
 int /*<<< orphan*/  AP_FUNC_MEX4K ; 
 void* CEX4A_MAX_MOD_SIZE_2K ; 
 void* CEX4A_MAX_MOD_SIZE_4K ; 
 void* CEX4A_MIN_MOD_SIZE ; 
 void* CEX4C_MAX_MOD_SIZE ; 
 void* CEX4C_MIN_MOD_SIZE ; 
 int ENODEV ; 
 int ENOMEM ; 
 void* ZCRYPT_CEX3C ; 
 void* ZCRYPT_CEX4 ; 
 void* ZCRYPT_CEX5 ; 
 void* ZCRYPT_CEX6 ; 
 scalar_t__ ap_test_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,int) ; 
 struct ap_card* to_ap_card (int /*<<< orphan*/ *) ; 
 struct zcrypt_card* zcrypt_card_alloc () ; 
 int /*<<< orphan*/  zcrypt_card_free (struct zcrypt_card*) ; 
 int zcrypt_card_register (struct zcrypt_card*) ; 

__attribute__((used)) static int zcrypt_cex4_card_probe(struct ap_device *ap_dev)
{
	/*
	 * Normalized speed ratings per crypto adapter
	 * MEX_1k, MEX_2k, MEX_4k, CRT_1k, CRT_2k, CRT_4k, RNG, SECKEY
	 */
	static const int CEX4A_SPEED_IDX[] = {
		 14, 19, 249, 42, 228, 1458, 0, 0};
	static const int CEX5A_SPEED_IDX[] = {
		  8,  9,  20, 18,  66,	458, 0, 0};
	static const int CEX6A_SPEED_IDX[] = {
		  6,  9,  20, 17,  65,	438, 0, 0};

	static const int CEX4C_SPEED_IDX[] = {
		 59,  69, 308, 83, 278, 2204, 209, 40};
	static const int CEX5C_SPEED_IDX[] = {
		 24,  31,  50, 37,  90,  479,  27, 10};
	static const int CEX6C_SPEED_IDX[] = {
		 16,  20,  32, 27,  77,  455,  23,  9};

	static const int CEX4P_SPEED_IDX[] = {
		224, 313, 3560, 359, 605, 2827, 0, 50};
	static const int CEX5P_SPEED_IDX[] = {
		 63,  84,  156,  83, 142,  533, 0, 10};
	static const int CEX6P_SPEED_IDX[] = {
		 55,  70,  121,  73, 129,  522, 0,  9};

	struct ap_card *ac = to_ap_card(&ap_dev->device);
	struct zcrypt_card *zc;
	int rc = 0;

	zc = zcrypt_card_alloc();
	if (!zc)
		return -ENOMEM;
	zc->card = ac;
	ac->private = zc;
	if (ap_test_bit(&ac->functions, AP_FUNC_ACCEL)) {
		if (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX4) {
			zc->type_string = "CEX4A";
			zc->user_space_type = ZCRYPT_CEX4;
			memcpy(zc->speed_rating, CEX4A_SPEED_IDX,
			       sizeof(CEX4A_SPEED_IDX));
		} else if (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX5) {
			zc->type_string = "CEX5A";
			zc->user_space_type = ZCRYPT_CEX5;
			memcpy(zc->speed_rating, CEX5A_SPEED_IDX,
			       sizeof(CEX5A_SPEED_IDX));
		} else {
			zc->type_string = "CEX6A";
			zc->user_space_type = ZCRYPT_CEX6;
			memcpy(zc->speed_rating, CEX6A_SPEED_IDX,
			       sizeof(CEX6A_SPEED_IDX));
		}
		zc->min_mod_size = CEX4A_MIN_MOD_SIZE;
		if (ap_test_bit(&ac->functions, AP_FUNC_MEX4K) &&
		    ap_test_bit(&ac->functions, AP_FUNC_CRT4K)) {
			zc->max_mod_size = CEX4A_MAX_MOD_SIZE_4K;
			zc->max_exp_bit_length =
				CEX4A_MAX_MOD_SIZE_4K;
		} else {
			zc->max_mod_size = CEX4A_MAX_MOD_SIZE_2K;
			zc->max_exp_bit_length =
				CEX4A_MAX_MOD_SIZE_2K;
		}
	} else if (ap_test_bit(&ac->functions, AP_FUNC_COPRO)) {
		if (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX4) {
			zc->type_string = "CEX4C";
			/* wrong user space type, must be CEX4
			 * just keep it for cca compatibility
			 */
			zc->user_space_type = ZCRYPT_CEX3C;
			memcpy(zc->speed_rating, CEX4C_SPEED_IDX,
			       sizeof(CEX4C_SPEED_IDX));
		} else if (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX5) {
			zc->type_string = "CEX5C";
			/* wrong user space type, must be CEX5
			 * just keep it for cca compatibility
			 */
			zc->user_space_type = ZCRYPT_CEX3C;
			memcpy(zc->speed_rating, CEX5C_SPEED_IDX,
			       sizeof(CEX5C_SPEED_IDX));
		} else {
			zc->type_string = "CEX6C";
			/* wrong user space type, must be CEX6
			 * just keep it for cca compatibility
			 */
			zc->user_space_type = ZCRYPT_CEX3C;
			memcpy(zc->speed_rating, CEX6C_SPEED_IDX,
			       sizeof(CEX6C_SPEED_IDX));
		}
		zc->min_mod_size = CEX4C_MIN_MOD_SIZE;
		zc->max_mod_size = CEX4C_MAX_MOD_SIZE;
		zc->max_exp_bit_length = CEX4C_MAX_MOD_SIZE;
	} else if (ap_test_bit(&ac->functions, AP_FUNC_EP11)) {
		if (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX4) {
			zc->type_string = "CEX4P";
			zc->user_space_type = ZCRYPT_CEX4;
			memcpy(zc->speed_rating, CEX4P_SPEED_IDX,
			       sizeof(CEX4P_SPEED_IDX));
		} else if (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX5) {
			zc->type_string = "CEX5P";
			zc->user_space_type = ZCRYPT_CEX5;
			memcpy(zc->speed_rating, CEX5P_SPEED_IDX,
			       sizeof(CEX5P_SPEED_IDX));
		} else {
			zc->type_string = "CEX6P";
			zc->user_space_type = ZCRYPT_CEX6;
			memcpy(zc->speed_rating, CEX6P_SPEED_IDX,
			       sizeof(CEX6P_SPEED_IDX));
		}
		zc->min_mod_size = CEX4C_MIN_MOD_SIZE;
		zc->max_mod_size = CEX4C_MAX_MOD_SIZE;
		zc->max_exp_bit_length = CEX4C_MAX_MOD_SIZE;
	} else {
		zcrypt_card_free(zc);
		return -ENODEV;
	}
	zc->online = 1;

	rc = zcrypt_card_register(zc);
	if (rc) {
		ac->private = NULL;
		zcrypt_card_free(zc);
	}

	return rc;
}