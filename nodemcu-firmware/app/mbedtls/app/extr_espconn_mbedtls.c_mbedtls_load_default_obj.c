#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
typedef  int uint16 ;
typedef  TYPE_1__* pmbedtls_parame ;
struct TYPE_5__ {int parame_datalen; char* parame_data; int parame_type; scalar_t__ parame_sec; } ;

/* Variables and functions */
 int ESPCONN_FORMAT_DER ; 
 int ESPCONN_FORMAT_INIT ; 
 int ESPCONN_FORMAT_PEM ; 
 scalar_t__ ESPCONN_INVALID_TYPE ; 
 int ESPCONN_PK ; 
 scalar_t__ FLASH_SECTOR_SIZE ; 
 TYPE_1__* def_certificate ; 
 TYPE_1__* def_private_key ; 
 TYPE_1__* mbedtls_parame_new (int) ; 
 int /*<<< orphan*/  os_memcpy (char*,unsigned char const*,int) ; 
 scalar_t__ os_strstr (unsigned char const*,char const* const) ; 
 int /*<<< orphan*/  spi_flash_read (scalar_t__,scalar_t__*,int) ; 

bool mbedtls_load_default_obj(uint32 flash_sector, int obj_type, const unsigned char *load_buf, uint16 length)
{
	pmbedtls_parame mbedtls_write = NULL;
	uint32 mbedtls_head = 0;
	bool mbedtls_load_flag = false;

	if (flash_sector != 0){
		spi_flash_read(flash_sector * FLASH_SECTOR_SIZE, (uint32*)&mbedtls_head, 4);
		if (mbedtls_head != ESPCONN_INVALID_TYPE){
			mbedtls_write = mbedtls_parame_new(0);
			mbedtls_write->parame_datalen = length;
		}
	} else{
		const char* const begin = "-----BEGIN";
		int format_type = ESPCONN_FORMAT_INIT;
		/*
	     * Determine data content. data contains either one DER certificate or
	     * one or more PEM certificates.
	     */
		if ((char*)os_strstr(load_buf, begin) != NULL){
			format_type = ESPCONN_FORMAT_PEM;
		}else{
			format_type = ESPCONN_FORMAT_DER;
		}

		if (format_type == ESPCONN_FORMAT_PEM){
			length += 1;
		}

		mbedtls_write = mbedtls_parame_new(length);
		if (mbedtls_write){
			os_memcpy(mbedtls_write->parame_data, load_buf, length);
			if (format_type == ESPCONN_FORMAT_PEM)
				mbedtls_write->parame_data[length - 1] = '\0';
		}
	}

	if (mbedtls_write){
		mbedtls_load_flag = true;
		mbedtls_write->parame_type = obj_type;
		mbedtls_write->parame_sec = flash_sector;
		if (obj_type == ESPCONN_PK){
			def_private_key = mbedtls_write;
		} else{
			def_certificate = mbedtls_write;
		}
	}
	return mbedtls_load_flag;
}