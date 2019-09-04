#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  scalar_t__ uint16 ;
struct TYPE_16__ {int auth_level; int /*<<< orphan*/  auth_type; } ;
typedef  TYPE_7__ mbedtls_auth_info ;
typedef  scalar_t__ int32 ;
struct TYPE_14__ {int sector; } ;
struct TYPE_13__ {int sector; } ;
struct TYPE_15__ {TYPE_5__ cert_req_sector; TYPE_4__ cert_ca_sector; } ;
struct TYPE_11__ {int sector; } ;
struct TYPE_10__ {int sector; } ;
struct TYPE_12__ {TYPE_2__ cert_req_sector; TYPE_1__ cert_ca_sector; } ;
struct TYPE_17__ {TYPE_6__ server; TYPE_3__ client; } ;

/* Variables and functions */
#define  ESPCONN_CERT_AUTH 132 
#define  ESPCONN_CERT_OWN 131 
#define  ESPCONN_CLIENT 130 
#define  ESPCONN_PK 129 
 scalar_t__ ESPCONN_SECURE_MAX_SIZE ; 
#define  ESPCONN_SERVER 128 
 int /*<<< orphan*/  spi_flash_read (scalar_t__,void*,scalar_t__) ; 
 TYPE_8__ ssl_option ; 

__attribute__((used)) static bool espconn_ssl_read_param_from_flash(void *param, uint16 len, int32 offset, mbedtls_auth_info *auth_info)
{
	if (param == NULL || (len + offset) > ESPCONN_SECURE_MAX_SIZE) {
		return false;
	}

	uint32 FILE_PARAM_START_SEC = 0x3B;
	switch (auth_info->auth_level) {
		case ESPCONN_CLIENT:
			switch (auth_info->auth_type) {
				case ESPCONN_CERT_AUTH:
					FILE_PARAM_START_SEC = ssl_option.client.cert_ca_sector.sector;
					break;
				case ESPCONN_CERT_OWN:
				case ESPCONN_PK:
					FILE_PARAM_START_SEC = ssl_option.client.cert_req_sector.sector;
					break;
				default:
					return false;
			}
			break;
		case ESPCONN_SERVER:
			switch (auth_info->auth_type) {
				case ESPCONN_CERT_AUTH:
					FILE_PARAM_START_SEC = ssl_option.server.cert_ca_sector.sector;
					break;
				case ESPCONN_CERT_OWN:
				case ESPCONN_PK:
					FILE_PARAM_START_SEC = ssl_option.server.cert_req_sector.sector;
					break;
				default:
					return false;
			}
			break;
		default:
			return false;
			break;
	}

	spi_flash_read(FILE_PARAM_START_SEC * 4096 + offset, param, len);

	return true;
}