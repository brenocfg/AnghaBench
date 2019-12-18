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
typedef  int uint32_t ;

/* Variables and functions */
#define  OMX_COLOR_Format12bitRGB444 183 
#define  OMX_COLOR_Format16bitARGB1555 182 
#define  OMX_COLOR_Format16bitARGB4444 181 
#define  OMX_COLOR_Format16bitBGR565 180 
#define  OMX_COLOR_Format16bitRGB565 179 
#define  OMX_COLOR_Format18BitBGR666 178 
#define  OMX_COLOR_Format18bitARGB1665 177 
#define  OMX_COLOR_Format18bitRGB666 176 
#define  OMX_COLOR_Format19bitARGB1666 175 
#define  OMX_COLOR_Format24BitABGR6666 174 
#define  OMX_COLOR_Format24BitARGB6666 173 
#define  OMX_COLOR_Format24bitARGB1887 172 
#define  OMX_COLOR_Format24bitBGR888 171 
#define  OMX_COLOR_Format24bitRGB888 170 
#define  OMX_COLOR_Format25bitARGB1888 169 
#define  OMX_COLOR_Format32bitARGB8888 168 
#define  OMX_COLOR_Format32bitBGRA8888 167 
#define  OMX_COLOR_Format8bitRGB332 166 
#define  OMX_COLOR_FormatAndroidOpaque 165 
#define  OMX_COLOR_FormatCbYCrY 164 
#define  OMX_COLOR_FormatCrYCbY 163 
#define  OMX_COLOR_FormatL16 162 
#define  OMX_COLOR_FormatL2 161 
#define  OMX_COLOR_FormatL24 160 
#define  OMX_COLOR_FormatL32 159 
#define  OMX_COLOR_FormatL4 158 
#define  OMX_COLOR_FormatL8 157 
#define  OMX_COLOR_FormatMonochrome 156 
#define  OMX_COLOR_FormatRawBayer10bit 155 
#define  OMX_COLOR_FormatRawBayer8bit 154 
#define  OMX_COLOR_FormatRawBayer8bitcompressed 153 
#define  OMX_COLOR_FormatUnused 152 
#define  OMX_COLOR_FormatYCbYCr 151 
#define  OMX_COLOR_FormatYCrYCb 150 
#define  OMX_COLOR_FormatYUV411PackedPlanar 149 
#define  OMX_COLOR_FormatYUV411Planar 148 
#define  OMX_COLOR_FormatYUV420PackedPlanar 147 
#define  OMX_COLOR_FormatYUV420PackedSemiPlanar 146 
#define  OMX_COLOR_FormatYUV420Planar 145 
#define  OMX_COLOR_FormatYUV420SemiPlanar 144 
#define  OMX_COLOR_FormatYUV422PackedPlanar 143 
#define  OMX_COLOR_FormatYUV422PackedSemiPlanar 142 
#define  OMX_COLOR_FormatYUV422Planar 141 
#define  OMX_COLOR_FormatYUV422SemiPlanar 140 
#define  OMX_COLOR_FormatYUV444Interleaved 139 
#define  OMX_QCOM_COLOR_FormatYUV420PackedSemiPlanar32m 138 
#define  OMX_QCOM_COLOR_FormatYUV420PackedSemiPlanar64x32Tile2m8ka 137 
#define  OMX_QCOM_COLOR_FormatYVU420SemiPlanar 136 
#define  OMX_SEC_COLOR_FormatNV12Tiled 135 
#define  OMX_TI_COLOR_FormatYUV420PackedSemiPlanar 134 
#define  QOMX_COLOR_FORMATYUV420PackedSemiPlanar32mCompressed 133 
#define  QOMX_COLOR_FORMATYUV420PackedSemiPlanar32mMultiView 132 
#define  QOMX_COLOR_Format32bitRGBA8888 131 
#define  QOMX_COLOR_Format32bitRGBA8888Compressed 130 
#define  QOMX_COLOR_FormatYUV420PackedSemiPlanar16m2ka 129 
#define  QOMX_COLOR_FormatYVU420PackedSemiPlanar32m4ka 128 

__attribute__((used)) static const char* omx_color_fomat_name(uint32_t format) {
  switch (format) {
  case OMX_COLOR_FormatUnused: return "OMX_COLOR_FormatUnused";
  case OMX_COLOR_FormatMonochrome: return "OMX_COLOR_FormatMonochrome";
  case OMX_COLOR_Format8bitRGB332: return "OMX_COLOR_Format8bitRGB332";
  case OMX_COLOR_Format12bitRGB444: return "OMX_COLOR_Format12bitRGB444";
  case OMX_COLOR_Format16bitARGB4444: return "OMX_COLOR_Format16bitARGB4444";
  case OMX_COLOR_Format16bitARGB1555: return "OMX_COLOR_Format16bitARGB1555";
  case OMX_COLOR_Format16bitRGB565: return "OMX_COLOR_Format16bitRGB565";
  case OMX_COLOR_Format16bitBGR565: return "OMX_COLOR_Format16bitBGR565";
  case OMX_COLOR_Format18bitRGB666: return "OMX_COLOR_Format18bitRGB666";
  case OMX_COLOR_Format18bitARGB1665: return "OMX_COLOR_Format18bitARGB1665";
  case OMX_COLOR_Format19bitARGB1666: return "OMX_COLOR_Format19bitARGB1666";
  case OMX_COLOR_Format24bitRGB888: return "OMX_COLOR_Format24bitRGB888";
  case OMX_COLOR_Format24bitBGR888: return "OMX_COLOR_Format24bitBGR888";
  case OMX_COLOR_Format24bitARGB1887: return "OMX_COLOR_Format24bitARGB1887";
  case OMX_COLOR_Format25bitARGB1888: return "OMX_COLOR_Format25bitARGB1888";
  case OMX_COLOR_Format32bitBGRA8888: return "OMX_COLOR_Format32bitBGRA8888";
  case OMX_COLOR_Format32bitARGB8888: return "OMX_COLOR_Format32bitARGB8888";
  case OMX_COLOR_FormatYUV411Planar: return "OMX_COLOR_FormatYUV411Planar";
  case OMX_COLOR_FormatYUV411PackedPlanar: return "OMX_COLOR_FormatYUV411PackedPlanar";
  case OMX_COLOR_FormatYUV420Planar: return "OMX_COLOR_FormatYUV420Planar";
  case OMX_COLOR_FormatYUV420PackedPlanar: return "OMX_COLOR_FormatYUV420PackedPlanar";
  case OMX_COLOR_FormatYUV420SemiPlanar: return "OMX_COLOR_FormatYUV420SemiPlanar";
  case OMX_COLOR_FormatYUV422Planar: return "OMX_COLOR_FormatYUV422Planar";
  case OMX_COLOR_FormatYUV422PackedPlanar: return "OMX_COLOR_FormatYUV422PackedPlanar";
  case OMX_COLOR_FormatYUV422SemiPlanar: return "OMX_COLOR_FormatYUV422SemiPlanar";
  case OMX_COLOR_FormatYCbYCr: return "OMX_COLOR_FormatYCbYCr";
  case OMX_COLOR_FormatYCrYCb: return "OMX_COLOR_FormatYCrYCb";
  case OMX_COLOR_FormatCbYCrY: return "OMX_COLOR_FormatCbYCrY";
  case OMX_COLOR_FormatCrYCbY: return "OMX_COLOR_FormatCrYCbY";
  case OMX_COLOR_FormatYUV444Interleaved: return "OMX_COLOR_FormatYUV444Interleaved";
  case OMX_COLOR_FormatRawBayer8bit: return "OMX_COLOR_FormatRawBayer8bit";
  case OMX_COLOR_FormatRawBayer10bit: return "OMX_COLOR_FormatRawBayer10bit";
  case OMX_COLOR_FormatRawBayer8bitcompressed: return "OMX_COLOR_FormatRawBayer8bitcompressed";
  case OMX_COLOR_FormatL2: return "OMX_COLOR_FormatL2";
  case OMX_COLOR_FormatL4: return "OMX_COLOR_FormatL4";
  case OMX_COLOR_FormatL8: return "OMX_COLOR_FormatL8";
  case OMX_COLOR_FormatL16: return "OMX_COLOR_FormatL16";
  case OMX_COLOR_FormatL24: return "OMX_COLOR_FormatL24";
  case OMX_COLOR_FormatL32: return "OMX_COLOR_FormatL32";
  case OMX_COLOR_FormatYUV420PackedSemiPlanar: return "OMX_COLOR_FormatYUV420PackedSemiPlanar";
  case OMX_COLOR_FormatYUV422PackedSemiPlanar: return "OMX_COLOR_FormatYUV422PackedSemiPlanar";
  case OMX_COLOR_Format18BitBGR666: return "OMX_COLOR_Format18BitBGR666";
  case OMX_COLOR_Format24BitARGB6666: return "OMX_COLOR_Format24BitARGB6666";
  case OMX_COLOR_Format24BitABGR6666: return "OMX_COLOR_Format24BitABGR6666";

  case OMX_COLOR_FormatAndroidOpaque: return "OMX_COLOR_FormatAndroidOpaque";
  case OMX_TI_COLOR_FormatYUV420PackedSemiPlanar: return "OMX_TI_COLOR_FormatYUV420PackedSemiPlanar";
  case OMX_QCOM_COLOR_FormatYVU420SemiPlanar: return "OMX_QCOM_COLOR_FormatYVU420SemiPlanar";
  case OMX_QCOM_COLOR_FormatYUV420PackedSemiPlanar64x32Tile2m8ka: return "OMX_QCOM_COLOR_FormatYUV420PackedSemiPlanar64x32Tile2m8ka";
  case OMX_SEC_COLOR_FormatNV12Tiled: return "OMX_SEC_COLOR_FormatNV12Tiled";
  case OMX_QCOM_COLOR_FormatYUV420PackedSemiPlanar32m: return "OMX_QCOM_COLOR_FormatYUV420PackedSemiPlanar32m";

  // case QOMX_COLOR_FormatYVU420SemiPlanar: return "QOMX_COLOR_FormatYVU420SemiPlanar";
  case QOMX_COLOR_FormatYVU420PackedSemiPlanar32m4ka: return "QOMX_COLOR_FormatYVU420PackedSemiPlanar32m4ka";
  case QOMX_COLOR_FormatYUV420PackedSemiPlanar16m2ka: return "QOMX_COLOR_FormatYUV420PackedSemiPlanar16m2ka";
  // case QOMX_COLOR_FormatYUV420PackedSemiPlanar64x32Tile2m8ka: return "QOMX_COLOR_FormatYUV420PackedSemiPlanar64x32Tile2m8ka";
  // case QOMX_COLOR_FORMATYUV420PackedSemiPlanar32m: return "QOMX_COLOR_FORMATYUV420PackedSemiPlanar32m";
  case QOMX_COLOR_FORMATYUV420PackedSemiPlanar32mMultiView: return "QOMX_COLOR_FORMATYUV420PackedSemiPlanar32mMultiView";
  case QOMX_COLOR_FORMATYUV420PackedSemiPlanar32mCompressed: return "QOMX_COLOR_FORMATYUV420PackedSemiPlanar32mCompressed";
  case QOMX_COLOR_Format32bitRGBA8888: return "QOMX_COLOR_Format32bitRGBA8888";
  case QOMX_COLOR_Format32bitRGBA8888Compressed: return "QOMX_COLOR_Format32bitRGBA8888Compressed";

  default:
    return "unkn";
  }
}