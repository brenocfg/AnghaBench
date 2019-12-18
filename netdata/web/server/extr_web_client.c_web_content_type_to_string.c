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
typedef  int uint8_t ;

/* Variables and functions */
#define  CT_APPLICATION_FONT_WOFF 149 
#define  CT_APPLICATION_FONT_WOFF2 148 
#define  CT_APPLICATION_JSON 147 
#define  CT_APPLICATION_OCTET_STREAM 146 
#define  CT_APPLICATION_VND_MS_FONTOBJ 145 
#define  CT_APPLICATION_XML 144 
#define  CT_APPLICATION_X_FONT_OPENTYPE 143 
#define  CT_APPLICATION_X_FONT_TRUETYPE 142 
#define  CT_APPLICATION_X_JAVASCRIPT 141 
#define  CT_IMAGE_BMP 140 
#define  CT_IMAGE_GIF 139 
#define  CT_IMAGE_ICNS 138 
#define  CT_IMAGE_JPG 137 
#define  CT_IMAGE_PNG 136 
#define  CT_IMAGE_SVG_XML 135 
#define  CT_IMAGE_XICON 134 
#define  CT_PROMETHEUS 133 
#define  CT_TEXT_CSS 132 
#define  CT_TEXT_HTML 131 
#define  CT_TEXT_PLAIN 130 
#define  CT_TEXT_XML 129 
#define  CT_TEXT_XSL 128 

const char *web_content_type_to_string(uint8_t contenttype) {
    switch(contenttype) {
        case CT_TEXT_HTML:
            return "text/html; charset=utf-8";

        case CT_APPLICATION_XML:
            return "application/xml; charset=utf-8";

        case CT_APPLICATION_JSON:
            return "application/json; charset=utf-8";

        case CT_APPLICATION_X_JAVASCRIPT:
            return "application/x-javascript; charset=utf-8";

        case CT_TEXT_CSS:
            return "text/css; charset=utf-8";

        case CT_TEXT_XML:
            return "text/xml; charset=utf-8";

        case CT_TEXT_XSL:
            return "text/xsl; charset=utf-8";

        case CT_APPLICATION_OCTET_STREAM:
            return "application/octet-stream";

        case CT_IMAGE_SVG_XML:
            return "image/svg+xml";

        case CT_APPLICATION_X_FONT_TRUETYPE:
            return "application/x-font-truetype";

        case CT_APPLICATION_X_FONT_OPENTYPE:
            return "application/x-font-opentype";

        case CT_APPLICATION_FONT_WOFF:
            return "application/font-woff";

        case CT_APPLICATION_FONT_WOFF2:
            return "application/font-woff2";

        case CT_APPLICATION_VND_MS_FONTOBJ:
            return "application/vnd.ms-fontobject";

        case CT_IMAGE_PNG:
            return "image/png";

        case CT_IMAGE_JPG:
            return "image/jpeg";

        case CT_IMAGE_GIF:
            return "image/gif";

        case CT_IMAGE_XICON:
            return "image/x-icon";

        case CT_IMAGE_BMP:
            return "image/bmp";

        case CT_IMAGE_ICNS:
            return "image/icns";

        case CT_PROMETHEUS:
            return "text/plain; version=0.0.4";

        default:
        case CT_TEXT_PLAIN:
            return "text/plain; charset=utf-8";
    }
}