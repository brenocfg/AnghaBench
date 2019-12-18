#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  calculated_number ;
struct TYPE_4__ {int /*<<< orphan*/  contenttype; } ;
typedef  TYPE_1__ BUFFER ;

/* Variables and functions */
 int BADGE_HORIZONTAL_PADDING ; 
 int /*<<< orphan*/  COLOR_STRING_SIZE ; 
 int /*<<< orphan*/  CT_IMAGE_SVG_XML ; 
 int /*<<< orphan*/  LABEL_STRING_SIZE ; 
 int RRDR_OPTION_DISPLAY_ABS ; 
 int /*<<< orphan*/  VALUE_STRING_SIZE ; 
 int /*<<< orphan*/  buffer_sprintf (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  calc_colorz (char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calculated_number_fabs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceil (double) ; 
 char* color_map (char const*) ; 
 int /*<<< orphan*/  escape_xmlz (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_value_and_unit (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ isinf (int /*<<< orphan*/ ) ; 
 scalar_t__ isnan (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int verdana11_width (char const*,double) ; 

void buffer_svg(BUFFER *wb, const char *label, calculated_number value, const char *units, const char *label_color, const char *value_color, int precision, int scale, uint32_t options, int fixed_width_lbl, int fixed_width_val) {
    char    value_color_buffer[COLOR_STRING_SIZE + 1]
            , value_string[VALUE_STRING_SIZE + 1]
            , label_escaped[LABEL_STRING_SIZE + 1]
            , value_escaped[VALUE_STRING_SIZE + 1]
            , label_color_escaped[COLOR_STRING_SIZE + 1]
            , value_color_escaped[COLOR_STRING_SIZE + 1];

    double label_width = (double)fixed_width_lbl, value_width = (double)fixed_width_val, total_width;
    double height = 20.0, font_size = 11.0, text_offset = 5.8, round_corner = 3.0;

    if(scale < 100) scale = 100;

    if(unlikely(!label_color || !*label_color))
        label_color = "#555";

    if(unlikely(!value_color || !*value_color))
        value_color = (isnan(value) || isinf(value))?"#999":"#4c1";

    calc_colorz(value_color, value_color_buffer, COLOR_STRING_SIZE, value);
    format_value_and_unit(value_string, VALUE_STRING_SIZE, (options & RRDR_OPTION_DISPLAY_ABS)?calculated_number_fabs(value):value, units, precision);

    if(fixed_width_lbl <= 0 || fixed_width_val <= 0) {
        label_width = verdana11_width(label, font_size) + (BADGE_HORIZONTAL_PADDING * 2);
        value_width = verdana11_width(value_string, font_size) + (BADGE_HORIZONTAL_PADDING * 2);
    }
    total_width = label_width + value_width;

    escape_xmlz(label_escaped, label, LABEL_STRING_SIZE);
    escape_xmlz(value_escaped, value_string, VALUE_STRING_SIZE);
    escape_xmlz(label_color_escaped, color_map(label_color), COLOR_STRING_SIZE);
    escape_xmlz(value_color_escaped, color_map(value_color_buffer), COLOR_STRING_SIZE);

    wb->contenttype = CT_IMAGE_SVG_XML;

    total_width  = total_width * scale / 100.0;
    height       = height      * scale / 100.0;
    font_size    = font_size   * scale / 100.0;
    text_offset  = text_offset * scale / 100.0;
    label_width  = label_width * scale / 100.0;
    value_width  = value_width * scale / 100.0;
    round_corner = round_corner * scale / 100.0;

    // svg template from:
    // https://raw.githubusercontent.com/badges/shields/master/templates/flat-template.svg
    buffer_sprintf(wb,
        "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" width=\"%0.2f\" height=\"%0.2f\">"
            "<linearGradient id=\"smooth\" x2=\"0\" y2=\"100%%\">"
                "<stop offset=\"0\" stop-color=\"#bbb\" stop-opacity=\".1\"/>"
                "<stop offset=\"1\" stop-opacity=\".1\"/>"
            "</linearGradient>"
            "<mask id=\"round\">"
                "<rect class=\"bdge-ttl-width\" width=\"%0.2f\" height=\"%0.2f\" rx=\"%0.2f\" fill=\"#fff\"/>"
            "</mask>"
            "<g mask=\"url(#round)\">"
                "<rect class=\"bdge-rect-lbl\" width=\"%0.2f\" height=\"%0.2f\" fill=\"%s\"/>",
        total_width, height,
        total_width, height, round_corner,
        label_width, height, label_color_escaped); //<rect class="bdge-rect-lbl"

    if(fixed_width_lbl > 0 && fixed_width_val > 0) {
        buffer_sprintf(wb,
                "<clipPath id=\"lbl-rect\">"
                    "<rect class=\"bdge-rect-lbl\" width=\"%0.2f\" height=\"%0.2f\"/>"
                "</clipPath>",
        label_width, height); //<clipPath id="lbl-rect"> <rect class="bdge-rect-lbl"
    }

    buffer_sprintf(wb,
                "<rect class=\"bdge-rect-val\" x=\"%0.2f\" width=\"%0.2f\" height=\"%0.2f\" fill=\"%s\"/>",
        label_width, value_width, height, value_color_escaped);
    
    if(fixed_width_lbl > 0 && fixed_width_val > 0) {
        buffer_sprintf(wb,
                "<clipPath id=\"val-rect\">"
                    "<rect class=\"bdge-rect-val\" x=\"%0.2f\" width=\"%0.2f\" height=\"%0.2f\"/>"
                "</clipPath>",
        label_width, value_width, height);
    }

    buffer_sprintf(wb,
                "<rect class=\"bdge-ttl-width\" width=\"%0.2f\" height=\"%0.2f\" fill=\"url(#smooth)\"/>"
            "</g>"
            "<g fill=\"#fff\" text-anchor=\"middle\" font-family=\"DejaVu Sans,Verdana,Geneva,sans-serif\" font-size=\"%0.2f\">"
                "<text class=\"bdge-lbl-lbl\" x=\"%0.2f\" y=\"%0.0f\" fill=\"#010101\" fill-opacity=\".3\" clip-path=\"url(#lbl-rect)\">%s</text>"
                "<text class=\"bdge-lbl-lbl\" x=\"%0.2f\" y=\"%0.0f\" clip-path=\"url(#lbl-rect)\">%s</text>"
                "<text class=\"bdge-lbl-val\" x=\"%0.2f\" y=\"%0.0f\" fill=\"#010101\" fill-opacity=\".3\" clip-path=\"url(#val-rect)\">%s</text>"
                "<text class=\"bdge-lbl-val\" x=\"%0.2f\" y=\"%0.0f\" clip-path=\"url(#val-rect)\">%s</text>"
            "</g>",
        total_width, height,
        font_size,
        label_width / 2, ceil(height - text_offset), label_escaped,
        label_width / 2, ceil(height - text_offset - 1.0), label_escaped,
        label_width + value_width / 2 -1, ceil(height - text_offset), value_escaped,
        label_width + value_width / 2 -1, ceil(height - text_offset - 1.0), value_escaped);

    if(fixed_width_lbl <= 0 || fixed_width_val <= 0){
        buffer_sprintf(wb,
            "<script type=\"text/javascript\">"
                "var bdg_horiz_padding = %d;"
                "function netdata_bdge_each(list, attr, value){"
                    "Array.prototype.forEach.call(list, function(el){"
                        "el.setAttribute(attr, value);"
                    "});"
                "};"
                "var this_svg = document.currentScript.closest(\"svg\");"
                "var elem_lbl = this_svg.getElementsByClassName(\"bdge-lbl-lbl\");"
                "var elem_val = this_svg.getElementsByClassName(\"bdge-lbl-val\");"
                "var lbl_size = elem_lbl[0].getBBox();"
                "var val_size = elem_val[0].getBBox();"
                "var width_total = lbl_size.width + bdg_horiz_padding*2;"
                "this_svg.getElementsByClassName(\"bdge-rect-lbl\")[0].setAttribute(\"width\", width_total);"
                "netdata_bdge_each(elem_lbl, \"x\", (lbl_size.width / 2) + bdg_horiz_padding);"
                "netdata_bdge_each(elem_val, \"x\", width_total + (val_size.width / 2) + bdg_horiz_padding);"
                "var val_rect = this_svg.getElementsByClassName(\"bdge-rect-val\")[0];"
                "val_rect.setAttribute(\"width\", val_size.width + bdg_horiz_padding*2);"
                "val_rect.setAttribute(\"x\", width_total);"
                "width_total += val_size.width + bdg_horiz_padding*2;"
                "var width_update_elems = this_svg.getElementsByClassName(\"bdge-ttl-width\");"
                "netdata_bdge_each(width_update_elems, \"width\", width_total);"
                "this_svg.setAttribute(\"width\", width_total);"
                "</script>",
            BADGE_HORIZONTAL_PADDING);
    }
    buffer_sprintf(wb, "</svg>");
}