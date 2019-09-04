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
typedef  scalar_t__ UINT8 ;
typedef  int UINT32 ;
typedef  scalar_t__ INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  NVMEM_SHARED_MEM_FILEID ; 
 int /*<<< orphan*/  SMART_CONFIG_PROFILE_SIZE ; 
#define  WLAN_SEC_UNSEC 131 
#define  WLAN_SEC_WEP 130 
#define  WLAN_SEC_WPA 129 
#define  WLAN_SEC_WPA2 128 
 int /*<<< orphan*/  aes_decrypt (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ aes_read_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key ; 
 scalar_t__ nvmem_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int* profileArray ; 
 scalar_t__ wlan_add_profile (int const,scalar_t__*,int,int /*<<< orphan*/ *,int,int,int,int,scalar_t__*,int) ; 

INT32 wlan_smart_config_process()
{
	INT32	returnValue;
	UINT32 ssidLen, keyLen;
	UINT8 *decKeyPtr;
	UINT8 *ssidPtr;

	// read the key from EEPROM - fileID 12
	returnValue = aes_read_key(key);

	if (returnValue != 0)
		return returnValue;

	// read the received data from fileID #13 and parse it according to the followings:
	// 1) SSID LEN - not encrypted
	// 2) SSID - not encrypted
	// 3) KEY LEN - not encrypted. always 32 bytes long
	// 4) Security type - not encrypted
	// 5) KEY - encrypted together with true key length as the first byte in KEY
	//	 to elaborate, there are two corner cases:
	//		1) the KEY is 32 bytes long. In this case, the first byte does not represent KEY length
	//		2) the KEY is 31 bytes long. In this case, the first byte represent KEY length and equals 31
	returnValue = nvmem_read(NVMEM_SHARED_MEM_FILEID, SMART_CONFIG_PROFILE_SIZE, 0, profileArray);

	if (returnValue != 0)
		return returnValue;

	ssidPtr = &profileArray[1];

	ssidLen = profileArray[0];

	decKeyPtr = &profileArray[profileArray[0] + 3];

	aes_decrypt(decKeyPtr, key);
	if (profileArray[profileArray[0] + 1] > 16)
		aes_decrypt((UINT8 *)(decKeyPtr + 16), key);

	if (*(UINT8 *)(decKeyPtr +31) != 0)
	{
		if (*decKeyPtr == 31)
		{
			keyLen = 31;
			decKeyPtr++;
		}
		else
		{
			keyLen = 32;
		}
	}
	else
	{
		keyLen = *decKeyPtr;
		decKeyPtr++;
	}

	// add a profile
	switch (profileArray[profileArray[0] + 2])
	{
	case WLAN_SEC_UNSEC://None
		{
			returnValue = wlan_add_profile(profileArray[profileArray[0] + 2], 	// security type
				ssidPtr,		 					// SSID
				ssidLen, 							// SSID length
				NULL, 							// BSSID
				1,								// Priority
				0, 0, 0, 0, 0);

			break;
		}

	case WLAN_SEC_WEP://WEP
		{
			returnValue = wlan_add_profile(profileArray[profileArray[0] + 2], 	// security type
				ssidPtr, 							// SSID
				ssidLen, 							// SSID length
				NULL, 							// BSSID
				1,								// Priority
				keyLen,							// KEY length
				0, 								// KEY index
				0,
				decKeyPtr,						// KEY
				0);

			break;
		}

	case WLAN_SEC_WPA://WPA
	case WLAN_SEC_WPA2://WPA2
		{
			returnValue = wlan_add_profile(WLAN_SEC_WPA2, 	// security type
				ssidPtr,
				ssidLen,
				NULL, 							// BSSID
				1,								// Priority
				0x18,							// PairwiseCipher
				0x1e, 							// GroupCipher
				2,								// KEY management
				decKeyPtr,						// KEY
				keyLen);							// KEY length

			break;
		}
	}

	return returnValue;
}